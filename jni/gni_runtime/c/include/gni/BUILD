# TODO(b/202729782): Fix library wrapper package visibility
package(default_visibility = ["//visibility:public"])

licenses(["notice"])

INCLUDE_PREFIX = "//third_party/library_wrapper/public/runtime/c/include"

cc_library(
    name = "gni",
    hdrs = ["gni.h"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }),
)

cc_library(
    name = "task_error_codes",
    hdrs = ["task_error_codes.h"],
    strip_include_prefix = INCLUDE_PREFIX,
)

cc_library(
    name = "task",
    hdrs = ["task.h"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = [":task_error_codes"],
)

Fileset(
    name = "gni_fileset",
    out = "gni_out",
    entries = [
        FilesetEntry(
            files = [
                "gni.h",
                "task.h",
                "task_error_codes.h",
            ],
            destdir = "c/gni/",
        ),
    ],
    visibility = ["//third_party/library_wrapper:library_wrapper_group"],
)
