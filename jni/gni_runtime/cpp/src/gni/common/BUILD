package(default_visibility = ["//visibility:public"])

licenses(["restricted"])

INCLUDE_PREFIX = "//third_party/library_wrapper/public/runtime/cpp/src"

cc_library(
    name = "diagnostics",
    srcs = ["diagnostics.cpp"],
    hdrs = ["diagnostics.h"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        "//third_party/library_wrapper/public/runtime/cpp/include/gni:gni",
    ],
)

cc_library(
    name = "scoped_local_ref",
    hdrs = ["scoped_local_ref.h"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }),
)

cc_library(
    name = "jni_helper",
    srcs = ["jni_helper_impl.cpp"],
    hdrs = [
        "jni_helper.h",
        "jni_helper_impl.h",
    ],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        ":logger",
    ],
)

cc_library(
    name = "logger",
    srcs = select({
        "//tools/cc_target_os:android": [
            "logger_android.cpp",
        ],
        "//conditions:default": [
            "logger_default.cpp",
        ],
    }),
    hdrs = ["logger.h"],
    linkopts = select({
        "//tools/cc_target_os:android": [
            # Needed for __android_log_vprint().
            "-llog",
        ],
        "//conditions:default": [],
    }),
    strip_include_prefix = INCLUDE_PREFIX,
)

cc_library(
    name = "jni_boxed_type_util",
    srcs = ["jni_boxed_type_util.cpp"],
    hdrs = ["jni_boxed_type_util.h"],
    strip_include_prefix = INCLUDE_PREFIX,
    deps = select({
        "//tools/cc_target_os:android": [],
        "//conditions:default": [
            "//third_party/java/jdk:jni",
        ],
    }) + [
        ":logger",
        "//third_party/library_wrapper/public/runtime/cpp/include/gni:gni",
    ],
)

Fileset(
    name = "common_libwrapper_fileset",
    out = "common_libwrapper_fileset_out",
    entries = [
        FilesetEntry(
            # omitting srcdir ==> it refers to the current package
            files = [
                "jni_boxed_type_util.cpp",
                "jni_boxed_type_util.h",
                "jni_helper.h",
                "jni_helper_impl.cpp",
                "jni_helper_impl.h",
                "logger.h",
                "logger_android.cpp",
                "scoped_local_ref.h",
            ],
            destdir = "cpp/gni/common/",
        ),
    ],
)
