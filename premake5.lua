function concat_arrays(arr1, arr2)
	local result = {}
	local n = 0
	for i = 1, #arr1 do
		n = n + 1
		result[n] = arr1[i]
	end
	for i = 1, #arr2 do
		n = n + 1
		result[n] = arr2[i]
	end

	return result
end

local coreheaders = { "include/**.h" }
local coresrcs_windows = { "src/windows/**.c" }
local coresrcs_posix = { "src/posix/**.c" }

local serverexampleheaders = concat_arrays(coreheaders, {})
local serverexamplesrcs = { "examples/server.c" }

local clientexampleheaders = concat_arrays(coreheaders, {})
local clientexamplesrcs = { "examples/client.c" }

workspace("tinytcp")
language("C")
cdialect("C11")
includedirs({ "include" })
configurations({ "Debug", "Release" })
defines({ "TINYTCP_CONFIG_BUILDING" })
filter({ "toolset:gcc or toolset:clang" })
buildoptions({ "-Wall", "-Wextra", "-Wpedantic" })
filter({}) -- Clear filters
filter({ "toolset:msc" })
buildoptions({ "/W4" })
defines({ "_CRT_SECURE_NO_WARNINGS" })
filter({}) -- Clear filters
filter({ "configurations:Release" })
defines({ "NDEBUG" })
symbols("Off")
optimize("On")
filter({}) -- Clear filters
filter({ "configurations:Debug" })
defines({ "DEBUG" })
symbols("On")
optimize("Off")

newoption({
	trigger = "shared",
	description = "Make a shared library instead of the a static one.",
})

project("tinytcp")
if _OPTIONS["shared"] then
	kind("SharedLib")
	defines({ "TINYTCP_CONFIG_SHARED" })
	filter({"system:not windows"})
	buildoptions({"-fPIC"})
	filter({}) -- Clear filters
else
	kind("StaticLib")
end
filter({"system:windows"})
files(concat_arrays(coreheaders, coresrcs_windows))
filter({}) -- Clear filters
filter({"system:not windows"})
files(concat_arrays(coreheaders, coresrcs_posix))
filter({}) -- Clear filters

project("tinytcp-server-example")
kind("ConsoleApp")
files(concat_arrays(serverexampleheaders, serverexamplesrcs))
links({"tinytcp"})

project("tinytcp-client-example")
kind("ConsoleApp")
files(concat_arrays(clientexampleheaders, clientexamplesrcs))
links({"tinytcp"})
