# TODO(b/202729782): Fix library wrapper package visibility
package(default_visibility = ["//visibility:public"])

licenses(["notice"])

INCLUDE_PREFIX = "//third_party/library_wrapper/public/runtime/cpp/include"

cc_library(
    name = "gni",
    hdrs = [
        "gni.hpp",
        "object.hpp",
    ],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }),
)

cc_library(
    name = "task",
    hdrs = ["task.hpp"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        "//third_party/library_wrapper/public/runtime/c/include/gni:task_error_codes",
    ],
)

Fileset(
    name = "gni_fileset",
    out = "gni_fileset_out",
    entries = [
        FilesetEntry(
            files = [
                "gni.hpp",
                "object.hpp",
                "task.hpp",
            ],
            destdir = "cpp/gni/",
        ),
    ],
    visibility = ["//third_party/library_wrapper:library_wrapper_group"],
)
