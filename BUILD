package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "chargez",
    srcs = ["main.cc"],
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
    ],
    deps = [
        ":screens",
        "@libgam//:game",
    ],
)

cc_library(
    name = "screens",
    srcs = [
        "game_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "game_screen.h",
        "title_screen.h",
    ],
    deps = [
        ":common",
        ":enemies",
        ":entity",
        ":player",
        ":space",
        "@libgam//:screen",
        "@libgam//:sprite",
        "@libgam//:spritemap",
        "@libgam//:text",
    ],
)

cc_library(
    name = "space",
    srcs = ["space.cc"],
    hdrs = ["space.h"],
    deps = [
        ":config",
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    deps = ["@libgam//:game"],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":common",
        ":entity",
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "common",
    hdrs = ["common.h"],
    srcs = ["common.cc"],
)

cc_library(
    name = "entity",
    hdrs = ["entity.h"],
    srcs = ["entity.cc"],
    deps = [
        ":common",
        ":config",
        "@libgam//:graphics",
        "@libgam//:spritemap",
    ],
)

cc_library(
    name = "enemies",
    hdrs = [
        "dizzy_jon.h",
        "dodgy_boi.h",
        "hacker.h",
        "kickler.h",
        "pawn.h",
        "pusher.h",
    ],
    srcs = [
        "dizzy_jon.cc",
        "dodgy_boi.cc",
        "hacker.cc",
        "kickler.cc",
        "pawn.cc",
        "pusher.cc",
    ],
    deps = [":entity"],
)
