#include <iostream>
#include <type_traits>

#define TRIGGER_STATIC(type)		  static constexpr type
#define TRIGGER_REDEFINE(type, alias) typedef type alias;
#define TRIGGER_USING(type, alias) using alias = type;

template <std::size_t TriggerId, typename TriggerAction, typename... RemainingAction>
class basic_trigger : public basic_trigger<TriggerId + 1, RemainingAction...>
{
public:
	TRIGGER_STATIC(std::size_t) id = TriggerId;
	TRIGGER_REDEFINE(TriggerAction, action_type)

public:
	template <typename... ExecArgs>
	void operator()(ExecArgs&&... args) { __M_trigger_action(std::forward<ExecArgs>(args)...) }

private:
	action_type __M_trigger_action;
};

template <std::size_t TriggerId, typename TriggerAction>
class basic_trigger<TriggerId, TriggerAction>
{
public:
	TRIGGER_STATIC(std::size_t) id = TriggerId;
	TRIGGER_REDEFINE(TriggerAction, action_type)

public:
	template <typename... ExecArgs>
	void operator()(ExecArgs&&... args) { __M_trigger_action(std::forward<ExecArgs>(args)...) }

private:
	action_type __M_trigger_action;
};

template <typename... TriggerAction>
class trigger_set
{
public:
	typedef basic_trigger<0, TriggerAction...> trigger_type;
	

private:
	trigger_type __M_trigger_set;
};

template <std::size_t N>
struct __helper_get
{
	static constexpr 
};

int main()
{

}