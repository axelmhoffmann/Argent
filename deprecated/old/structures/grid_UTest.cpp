#include "../../TestFramework.h"
#include "core/structures/grid.h"

namespace grid_test
{
	$UTest(grid);

	$Case(box_query, grid)
	{
		agt::grid<int> gr(5, 5, 1);

		size_t count;
		count = gr.query_box(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f }).size();
		ag_expect(count == 0, "Expected 0 results when querying an empty grid, found {}", count);

		gr.insert(1, { 1.0f, 1.0f });
		count = gr.query_box(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f }).size();
		ag_expect(count == 1, "Expected 1 result when querying an occupied grid, found {}", count);
		// Outside our query zone
		gr.insert(1, { 1.6f, 3.5f });
		count = gr.query_box(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f }).size();
		ag_expect(count == 1, "Expected 1 result when querying an occupied grid, found {}", count);

		gr.insert(1, { 0.5f, 0.5f });
		gr.insert(1, { 1.5f, 1.5f });
		count = gr.query_box(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f }).size();
		ag_expect(count == 3, "Expected 3 results when querying an occupied grid, found {}", count);

		// Move query over
		count = gr.query_box(glm::vec2{ 1.5f, 1.5f }, glm::vec2{ 4.0f, 4.0f }).size();
		ag_expect(count == 2, "Expected 2 results when querying an occupied grid, found {}", count);

		count = gr.query_box(glm::vec2{ 1.6f, 1.6f }, glm::vec2{ 4.0f, 4.0f }).size();
		ag_expect(count == 1, "Expected 1 result when querying an occupied grid, found {}", count);
	}

	$Case(box_query_with_predicate, grid)
	{
		agt::grid<int> gr(5, 5, 1);

		size_t count;

		gr.insert(1, { 0.5f, 0.5f });
		gr.insert(5, { 1.0f, 1.0f });
		gr.insert(3, { 1.5f, 1.0f });
		gr.insert(2, { 1.2f, 1.0f });
		gr.insert(8, { 1.3f, 1.1f });
		// Check with predicate for even numbers
		count = gr.query_box(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f },
			[](auto x) { return x.val % 2 == 0; })
			.size();
		ag_expect(count == 2, "Expected 2 results when querying with predicate, found {}", count);
	}

	$Case(circle_query, grid)
	{
		agt::grid<int> gr(5, 5, 1);

		size_t count;

		// Empty
		count = gr.query_circle(glm::vec2{ 1.0f, 2.0f }, 1).size();
		ag_expect(count == 0, "Expected 0 results querying an empty grid, found {}", count);
		// Miss
		gr.insert(1, { 1.8f, 1.2f });
		count = gr.query_circle(glm::vec2{ 1.0f, 2.0f }, 1).size();
		ag_expect(count == 0, "Expected 0 results querying a miss on occupied grid, found {}", count);
		// 2 Hits
		gr.insert(1, { 0.5f, 2.5f });
		gr.insert(1, { 1.0f, 1.5f });
		count = gr.query_circle(glm::vec2{ 1.0f, 2.0f }, 1).size();
		ag_expect(count == 2, "Expected 2 results querying an occupied grid, found {}", count);

		gr.insert(1, { 2.0f, 2.5f });
	}

	$Case(circle_query_with_predicate, grid)
	{
		agt::grid<int> gr(5, 5, 1);

		size_t count;

		// Miss
		gr.insert(1, { 1.8f, 1.2f });
		// 5 in zone, 3 expected Hits
		gr.insert(11, { 0.5f, 2.5f });
		gr.insert(12, { 1.0f, 1.5f });
		gr.insert(11, { 0.5f, 2.0f });
		gr.insert(5, { 1.2f, 1.0f });
		gr.insert(6, { 0.8f, 2.0f });
		count = gr.query_circle(glm::vec2{ 1.0f, 2.0f }, 1,
			[](auto x) { return x.val > 10; })
			.size();

		ag_expect(count == 3, "Expected 3 results querying with a predicate an occupied grid, found {}", count);
	}
}