#pragma once
#include <cstddef>

#define unknown_value(size) [[maybe_unused]] std::byte _unk_ ## size [ size ]
#define vtable_entry virtual void _dummy_fn() = 0
#define unknown_virtual_func(placeholder_name) virtual void placeholder_name() = 0

typedef std::byte _unknown_value;
