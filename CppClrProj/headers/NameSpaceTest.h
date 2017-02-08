#pragma once

namespace Out{
	//inline 
	namespace Inner{
		class NameSpaceTest
		{
		public:
			NameSpaceTest(void);
			~NameSpaceTest(void);
		};
	}

	//using namespace Inner;

	static void x(){
		int i = static_cast<double>(12.0);
	}
}

