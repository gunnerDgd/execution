#pragma once
#include <type_traits>
#include <functional>

namespace execution::trigger {
	class on_executed  {  };
	class on_suspended {  };
	class on_resumed   {  };
	class on_yielded   {  };
	class on_stopped   {  };

	static constexpr on_executed  executed ;
	static constexpr on_suspended suspended;
	static constexpr on_resumed   resumed  ;
	static constexpr on_yielded   yielded  ;
	static constexpr on_stopped   stopped  ;
}

