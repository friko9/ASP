#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_traverse_last
	: public treeset_array_test_case
    {
	index_t index, retval;
	side_t side;
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container))
		    = make_data(tree_size,data);
	    }
	test_result test()
	    {
		auto ret = test_plug.traverse_last(container, root, side);
		return score_t(ret == retval);
	    }
    };

    struct populated_c_traverse_last_c_on_left_return_c
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0}};
		index = root;
		side = side_t::left;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_left_return_c);

    struct populated_c_traverse_last_c_on_right_return_c
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0}};
		index = root;
		side = side_t::right;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_right_return_c);

    struct populated_c_l_traverse_last_c_on_left_return_l
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1}};
		index = root;
		side = side_t::left;
		retval = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_left_return_l);

    struct populated_c_l_traverse_last_c_on_right_return_c
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1}};
		index = root;
		side = side_t::right;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_right_return_c);
    
    struct populated_c_r_traverse_last_c_on_left_return_c
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{3,1}};
		index = root;
		side = side_t::left;
		retval = root;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_left_return_c);
    
    struct populated_c_r_traverse_last_c_on_right_return_r
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{3,1}};
		index = root;
		side = side_t::right;
		retval = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_right_return_r);

    struct populated_c_l_r_traverse_last_c_on_left_return_l
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1},{3,1}};
		index = root;
		side = side_t::left;
		retval = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_left_return_l);

    struct populated_c_l_r_traverse_last_c_on_right_return_r
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1},{3,1}};
		index = root;
		side = side_t::right;
		retval = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_right_return_r);

    struct populated_lml_traverse_last_c_on_left_return_last_l
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,-10},{2,-20},{4,-30},{8,-40},{16,-50},{32,-60},{64,-70},{128,-80},{256,-90},{512,-100}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lml_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_traverse_last_c_on_right_return_last_r
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,10},{3,20},{7,30},{15,40},{31,50},{63,60},{127,70},{255,80},{511,90},{1023,100}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_traverse_last_c_on_right_return_last_r);
    
    struct populated_lml_lmlr_traverse_last_c_on_left_return_last_l
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,-10},{2,-20},{4,-30},{8,-40},{16,-50},{32,-60},{64,-70},{128,-80},{256,-90},{512,-100},{1025,-95}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lml_lmlr_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_rmrl_traverse_last_c_on_right_return_last_r
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,10},{3,20},{7,30},{15,40},{31,50},{63,60},{127,70},{255,80},{511,90},{1023,100},{2046,95}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_rmrl_traverse_last_c_on_right_return_last_r);

    struct populated_lrml_traverse_last_c_on_left_return_last_l
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{8,-30},{9,-15},{16,-40},{17,-25},{32,-50},{33,-35}
			,{64,-60},{63,-45},{128,-70},{129,-55},{256,-80},{257,-65},{512,-90},{513,-75},{1025,-85}};
		index = root;
		side = side_t::left;
		retval = 512;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lrml_traverse_last_c_on_left_return_last_l);

    struct populated_lrmr_traverse_last_c_on_right_return_last_r
    	: public treeset_array_test_traverse_last
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0},{2,-10},{3,10},{6,5},{7,20},{14,15},{15,30},{30,25},{31,40},{62,35},{63,50},{126,45}
			,{127,60},{254,55},{255,70},{510,65},{511,80},{1022,75},{1023,90},{2046,85}};
		index = root;
		side = side_t::right;
		retval = 1023;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lrmr_traverse_last_c_on_right_return_last_r);
}
