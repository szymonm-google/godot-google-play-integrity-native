# TODO(b/202729782): Fix library wrapper package visibility
package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "gni",
    srcs = [
        "gni.cpp",
        "object.cpp",
    ],
    copts = [
        "-fno-strict-aliasing",
        "-fno-exceptions",
    ],
    features = ["-use_header_modules"],
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        "//third_party/library_wrapper/public/runtime/cpp/src/gni/common:jni_helper",
        "//third_party/library_wrapper/public/runtime/c/include/gni:gni",
        "//third_party/library_wrapper/public/runtime/cpp/include/gni:gni",
        "//third_party/library_wrapper/public/runtime/cpp/src/gni/common:logger",
    ],
)

cc_library(
    name = "task",
    srcs = [
        "task.cpp",
    ],
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        ":gni",
        "//third_party/library_wrapper/public/runtime/c/include/gni:gni",
        "//third_party/library_wrapper/public/runtime/cpp/include/gni:gni",
        "//third_party/library_wrapper/public/runtime/c/src/gni:task_error_codes",
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
                "gni.cpp",
                "object.cpp",
                "task.cpp",
            ],
            destdir = "cpp/gni/",
        ),
    ],
    visibility = ["//third_party/library_wrapper:library_wrapper_group"],
)
