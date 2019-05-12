 {
    "targets": [
      {
        "target_name": "engine",
        "sources": [ 
          "main.cpp",
          "<!@(node -p \"require('fs').readdirSync('./src').map(f=>'src/'+f).join(' ')\")"
        ],
        "include_dirs" : [
          "./includes",
          "<!(node -e \"require('nan')\")"
        ]
      }
    ]
}