# TODO(b/202729782): Fix library wrapper package visibility
package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "gni",
    srcs = ["gni.cc"],
    deps = [
        "//third_party/library_wrapper/public/runtime/c/include/gni",
        "//third_party/library_wrapper/public/runtime/cpp/include/gni",
    ],
)

cc_library(
    name = "task_error_codes",
    srcs = ["task_error_codes.cc"],
    deps = ["//third_party/library_wrapper/public/runtime/c/include/gni:task_error_codes"],
)

cc_library(
    name = "task",
    srcs = [
        "task.cc",
    ],
    hdrs = [
        "task_internal.h",
    ],
    strip_include_prefix = "//third_party/library_wrapper/public/runtime/c/src",
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        "//third_party/library_wrapper/public/runtime/c/src/gni:task_error_codes",
        "//third_party/library_wrapper/public/runtime/cpp/src/gni:task",
        "//third_party/library_wrapper/public/runtime/c/include/gni:task_error_codes",
        "//third_party/library_wrapper/public/runtime/c/include/gni:task",
        "//third_party/library_wrapper/public/runtime/cpp/include/gni:task",
        "//third_party/library_wrapper/public/runtime/cpp/src/gni/common:logger",
    ],
)

Fileset(
    name = "gni_fileset",
    out = "gni_fileset_out",
    entries = [
        FilesetEntry(
            files = [
                "gni.cc",
                "task.cc",
                "task_error_codes.cc",
                "task_internal.h",
            ],
            destdir = "c/gni/",
        ),
    ],
    visibility = ["//third_party/library_wrapper:library_wrapper_group"],
)
