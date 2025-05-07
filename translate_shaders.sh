#!/usr/bin/env bash

rm -r shaders_h

set -e

SRC_DIR="shaders"
DST_DIR="shaders_h"

find "$SRC_DIR" -type f \( -name '*.glsl' -o -name '*.vert' -o -name '*.frag' \) | while read -r shader_file; do
    rel_path="${shader_file#$SRC_DIR/}"
    header_path="${rel_path%.*}.h"
    out_file="$DST_DIR/$header_path"
    mkdir -p "$(dirname "$out_file")"

    var_name=$(echo "$header_path" | tr '/.-' '___' | sed 's/___h$//')

    {
        echo "R\"("
        cat "$shader_file"
        echo ")\""
    } > "$out_file"

    echo "Converted $shader_file -> $out_file"
done

echo "All shader files have been converted to header files in $DST_DIR."
