//constexpr support
class key
{
public:

  constexpr key(int keycode, int modifiers): m_keycode{ keycode }, m_modifiers { modifiers } {}

  constexpr virtual ~key() = default;

  // a workaround over dynamic_cast for the keybind class 
  void constexpr virtual execBindedActionIfExists() {}

private:

  int m_keycode;
  int m_modifiers;

};
