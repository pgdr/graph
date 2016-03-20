#include "graph.hpp"
#include "doubleton.hpp"

#define BOOST_TEST_MODULE graph_test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ADD_VERTEX)
{
  graph g;
  BOOST_CHECK_EQUAL(g.size(),0);
  g.add_vertex();
  BOOST_CHECK_EQUAL(g.size(),1);
  g.add_vertex(4);
  BOOST_CHECK_EQUAL(g.size(),2);
}

// BOOST_AUTO_TEST_CASE(DELETE_VERTEX)
// {
//   graph g;
//   for (int i = 0; i < 10; ++i) g.add_vertex();
//   BOOST_CHECK_EQUAL(g.size(),10);
//   g.delete_vertex(5);
//   BOOST_CHECK_EQUAL(g.size(),9);
// }

BOOST_AUTO_TEST_CASE(IS_CONNECTED)
{
  graph g;
  for (int i = 0; i < 10; ++i) g.add_edge(i,i+1);
  BOOST_CHECK(g.is_connected());
}
