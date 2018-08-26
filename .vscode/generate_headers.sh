#!/bin/bash

if [ -z "${workspaceFolder}" ]; then
	workspaceFolder='.'
fi

workspaceFolder=`realpath "${workspaceFolder}"`

GLPP_HPP="${workspaceFolder}/glpp.hpp"

printf '#pragma once\n\n' > "${GLPP_HPP}"
printf '#include <GL/glew.h>\n\n' >> "${GLPP_HPP}"

cd "${workspaceFolder}/glpp/"
for header in *.hpp; do
	printf '#include "glpp/%s"\n' "${header}" >> "${GLPP_HPP}"
done

printf '\n\n' >> "${GLPP_HPP}"

printf '#ifndef GLPP_NO_INLINE\n\n' >> "${GLPP_HPP}"
printf '\t#define GLPP_INLINE\n' >> "${GLPP_HPP}"
printf '\t#define GLPP_DECL inline\n' >> "${GLPP_HPP}"

for source in *.cpp; do
	printf '\t#include "glpp/%s"\n' "${source}" >> "${GLPP_HPP}"
done
printf '\n#endif // (GLPP_NO_INLINE)\n' >> "${GLPP_HPP}"

exit

# GLPP_INL="${workspaceFolder}/glpp.inl"

# printf '' > "${GLPP_INL}"

# cd "${workspaceFolder}/glpp/"
# for source in *.cpp; do
# 	printf '#include "glpp/%s"\n' "${source}" >> "${GLPP_INL}"
# done