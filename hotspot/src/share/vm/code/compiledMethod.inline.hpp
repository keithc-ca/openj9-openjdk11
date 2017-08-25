/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef SHARE_VM_CODE_COMPILEDMETHOD_INLINE_HPP
#define SHARE_VM_CODE_COMPILEDMETHOD_INLINE_HPP

#include "code/compiledMethod.hpp"
#include "code/nativeInst.hpp"
#include "runtime/frame.hpp"

// When using JVMCI the address might be off by the size of a call instruction.
inline bool CompiledMethod::is_deopt_entry(address pc) {
  return pc == deopt_handler_begin()
#if INCLUDE_JVMCI
    || (is_compiled_by_jvmci() && pc == (deopt_handler_begin() + NativeCall::instruction_size))
#endif
    ;
}


// -----------------------------------------------------------------------------
// CompiledMethod::get_deopt_original_pc
//
// Return the original PC for the given PC if:
// (a) the given PC belongs to a nmethod and
// (b) it is a deopt PC

inline address CompiledMethod::get_deopt_original_pc(const frame* fr) {
  if (fr->cb() == NULL)  return NULL;

  CompiledMethod* cm = fr->cb()->as_compiled_method_or_null();
  if (cm != NULL && cm->is_deopt_pc(fr->pc()))
    return cm->get_original_pc(fr);

  return NULL;
}

#endif //SHARE_VM_CODE_COMPILEDMETHOD_INLINE_HPP
