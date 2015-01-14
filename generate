#!/bin/bash

DEFAULT_ORBITERAPI="C:/Orbiter 2010/Orbitersdk/include/OrbiterAPI.h"

if [[ "${1}" == "-h" || "${1}" == "--help" ]]; then
    echo "Usage: generate.sh [ /path/to/OrbiterAPI.h ]"
    echo "Default path: ${DEFAULT_ORBITERAPI}"
    echo
    exit 0
elif [[ -n "${1}" ]]; then
    ORBITERAPI="${1}"
else
    ORBITERAPI="${DEFAULT_ORBITERAPI}"
fi

sed -rne 's/^(\s*)(#define\s+)(OAPI_KEY_)([a-zA-Z0-9_]+)(\s+.*)$/{ "\4", \3\4 },/p' "${ORBITERAPI}" > keymap.inc
