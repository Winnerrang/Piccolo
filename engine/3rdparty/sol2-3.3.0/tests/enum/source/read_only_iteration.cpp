// sol2

// The MIT License (MIT)

// Copyright (c) 2013-2022 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <catch2/catch_all.hpp>

#include <sol/sol.hpp>

inline namespace sol2_tests_enum_read_only_iteration {
	enum class color { red, blue };
}


TEST_CASE("enum/read-only-iteration", "make sure iteration for read only tables works properly") {
	sol::state lua;
	lua.open_libraries(sol::lib::base);
#define TABLE_ENTRIES() "FIRST", 1, "SECOND", 2, "THIRD", 3, "NOT-FOURTH", 5
	lua.create_named_table("Check", TABLE_ENTRIES());
	lua.new_enum("Enum", TABLE_ENTRIES());
#undef TABLE_ENTRIES

	SECTION("without global next function") {
		sol::optional<sol::error> maybe_result = lua.safe_script("for k, v in pairs(Enum) do assert(Check[k] == v) end", sol::script_pass_on_error);
		REQUIRE_FALSE(maybe_result.has_value());
	}
	SECTION("with global next function") {
		lua.open_libraries(sol::lib::table);
		sol::optional<sol::error> maybe_result = lua.safe_script("for k, v in pairs(Enum) do assert(Check[k] == v) end", sol::script_pass_on_error);
		REQUIRE_FALSE(maybe_result.has_value());
	}
}
