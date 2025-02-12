#pragma once
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <algorithm>
#include <iterator>

#include <functional>

namespace agt
{
	template <typename value>
	struct grid
	{
		grid(int x, int y, float cell_size) : width(x), height(y), cellsize(cell_size)
		{
			data = new std::vector<node>*[x];
			for (size_t i = 0; i < x; i++)
			{
				data[i] = new std::vector<node>[y];
			}
		}

		~grid()
		{
			for (size_t i = 0; i < width; i++)
			{
				delete[] data[i];
			}
			delete[] data;
		}

		template <typename Predicate = decltype(default_predicate)>
		std::vector<value> query_box(glm::vec2 p1, glm::vec2 p2, Predicate predicate = default_predicate)
		{
			if (p1.x > p2.x) std::swap(p1.x, p2.x);
			if (p1.y > p2.y) std::swap(p1.y, p2.y);
			glm::ivec2 p1_grid = to_grid_coords(p1);
			glm::ivec2 p2_grid = to_grid_coords(p2);

			return query_box_filtered(p1_grid, p2_grid, 
				[=](node x) 
				{ 
					return (x.pos.x >= p1.x && x.pos.y >= p1.y) 
						&& (x.pos.x <= p2.x && x.pos.y <= p2.y) 
						&& predicate(x); 
				}
			);
		}

		template <typename Predicate = decltype(default_predicate)>
		std::vector<value> query_circle(glm::vec2 p, float r, Predicate predicate = default_predicate)
		{
			glm::ivec2 p1_grid = to_grid_coords({ p.x - r, p.y - r });
			glm::ivec2 p2_grid = to_grid_coords({ p.x + r, p.y + r });

			return query_box_filtered(p1_grid, p2_grid, 
				[=](node x)
				{
					return (glm::length(x.pos - p) <= r) && predicate(x); 
				}
			);
		}

		void insert(value val, glm::vec2 pos)
		{
			glm::ivec2 pos_grid = to_grid_coords(pos);
			data[pos_grid.x][pos_grid.y].push_back(node{ pos, val });
		}

	private:
		struct node
		{
			glm::vec2 pos;
			value val;
		};

		static inline const auto default_predicate = [](typename grid<value>::node x) -> bool { return true; };

		std::vector<value> query_box_filtered(glm::ivec2 p1_grid, glm::ivec2 p2_grid, auto predicate)
		{
			std::vector<value> out;
			for (size_t x = p1_grid.x; x < p2_grid.x; x++)
			{
				for (size_t y = p1_grid.y; y < p2_grid.y; y++)
				{
					/// TODO: can this be simplified?
					for (size_t i = 0; i < data[x][y].size(); i++)
					{
						if (predicate(data[x][y][i]))
							out.push_back(data[x][y][i].val);
					}
				}
			}
			return out;
		}

		std::vector<node>** data;
		int width;
		int height;
		float cellsize;

		bool in_bounds(glm::vec2 pos)
		{
			return (pos.x < 0 || pos.x > width ||
				pos.y < 0 || pos.y > height);
		}

		glm::ivec2 to_grid_coords(glm::vec2 pos)
		{
			glm::ivec2 out = { (int)(pos.x / cellsize), (int)(pos.y / cellsize) };
			out.x = out.x < 0 ? 0 : (out.x > width ? width : out.x);
			out.y = out.y < 0 ? 0 : (out.y > height ? height : out.y);
			return out;
		}
	};
}