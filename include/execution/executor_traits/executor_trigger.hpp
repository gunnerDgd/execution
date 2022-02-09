#pragma once

namespace execution::trigger_types {
	class on_executed  { };
	class on_return    { };
	class on_suspended { };
}

namespace execution::execution_types {
	
}

namespace execution {
	template <typename T>
	class trigger							   { static constexpr bool enabled = false; };

	template <>
	class trigger<trigger_types::on_executed>  { static constexpr bool enabled = true ; }; typedef trigger<trigger_types::on_executed>  on_executed;

	template <>
	class trigger<trigger_types::on_return>    { static constexpr bool enabled = true ; }; typedef trigger<trigger_types::on_return>    on_return;
	 
	template <>
	class trigger<trigger_types::on_suspended> { static constexpr bool enabled = true ; }; typedef trigger<trigger_types::on_suspended> on_suspended;

}