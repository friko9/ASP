#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_traverse_last
	: public treeset_array_balance_test_case
    {
	index_t index, retval;
	side_t side;
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container),
			 test_plug.get_heights(container))
		    = make_data(tree_size,data);
	    }
	test_result test()
	    {
		auto ret = test_plug.traverse_last(container, root, side);
		return score_t(ret == retval);
	    }
    };
    
    struct populated_c_traverse_last_c_on_left_return_c
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,1}};
		index = root;
		side = side_t::left;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_left_return_c);

    struct populated_c_traverse_last_c_on_right_return_c
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,1}};
		index = root;
		side = side_t::right;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_right_return_c);

    struct populated_c_l_traverse_last_c_on_left_return_l
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1}};
		index = root;
		side = side_t::left;
		retval = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_left_return_l);

    struct populated_c_l_traverse_last_c_on_right_return_c
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1}};
		index = root;
		side = side_t::right;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_right_return_c);
    
    struct populated_c_r_traverse_last_c_on_left_return_c
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{3,1,1}};
		index = root;
		side = side_t::left;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_left_return_c);
    
    struct populated_c_r_traverse_last_c_on_right_return_r
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{3,1,1}};
		index = root;
		side = side_t::right;
		retval = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_right_return_r);

    struct populated_c_l_r_traverse_last_c_on_left_return_l
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2}
			,{2,-1,1},{3,1,1}};
		index = root;
		side = side_t::left;
		retval = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_left_return_l);

    struct populated_c_l_r_traverse_last_c_on_right_return_r
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2}
			,{2,-1,1},{3,1,1}};
		index = root;
		side = side_t::right;
		retval = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_right_return_r);

    struct populated_lml_traverse_last_c_on_left_return_last_l
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,-10,10},{2,-20,9},{4,-30,8},{8,-40,7},{16,-50,6},{32,-60,5}
			,{64,-70,4},{128,-80,3},{256,-90,2},{512,-100,1}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lml_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_traverse_last_c_on_right_return_last_r
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,10,10},{3,20,9},{7,30,8},{15,40,7},{31,50,6},{63,60,5},{127,70,4},
			{255,80,3},{511,90,2},{1023,100,1}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_traverse_last_c_on_right_return_last_r);
    
    struct populated_lml_lmlr_traverse_last_c_on_left_return_last_l
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,-10,11},{2,-20,10},{4,-30,9},{8,-40,8},{16,-50,7},{32,-60,6},
			{64,-70,5},{128,-80,4},{256,-90,3},{512,-100,2},{1025,-95,1}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lml_lmlr_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_rmrl_traverse_last_c_on_right_return_last_r
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,10,11},{3,20,10},{7,30,9},{15,40,8},{31,50,7},{63,60,6},
			{127,70,5},{255,80,4},{511,90,3},{1023,100,2},{2046,95,1}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_rmrl_traverse_last_c_on_right_return_last_r);

    struct populated_lrml_traverse_last_c_on_left_return_last_l
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0,11},
			{2,-10,10},{3,10,1},
			{4,-20,9},{5,-5,1},
			{8,-30,8},{9,-15,1},
			{16,-40,7},{17,-25,1},
			{32,-50,6},{33,-35,1},
			{64,-60,5},{63,-45,1},
			{128,-70,4},{129,-55,1},
			{256,-80,3},{257,-65,1},
			{512,-90,2},{513,-75,1},
			{1025,-85,1}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lrml_traverse_last_c_on_left_return_last_l);

    struct populated_lrmr_traverse_last_c_on_right_return_last_r
	: public treeset_array_balance_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0,11},
			{2,-10,1},{3,10,10},
			{6,5,1},{7,20,9},
			{14,15,1},{15,30,8},
			{30,25,1},{31,40,7},
			{62,35,1},{63,50,6},
			{126,45,1},{127,60,5},
			{254,55,1},{255,70,4},
			{510,65,1},{511,80,3},
			{1022,75,1},{1023,90,2},
			{2046,85,1}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lrmr_traverse_last_c_on_right_return_last_r);
}
