{
  "targets": [{
    "target_name": "nativemodule",
    "defines": [ "NAPI_CPP_EXCEPTIONS" ],
    "cflags!": [ "-fno-exceptions" ],
    "cflags_cc!": [ "-fno-exceptions" ],
    "include_dirs": [
      "src",
      "<!(node -p \"require('node-addon-api').include_dir\")",
    ],
    "sources": [
      "src/binding.cc"
    ]
  }]
}
