#pragma once

#include <set>
#include "../util.h"
#include "../program.h"
#include "base.h"

TLANG_NAMESPACE_BEGIN

class Program;

class CPUCodeGen : public CodeGenBase {
 public:
  Program *prog;
  Kernel *current_kernel;
  std::map<int, std::string> masks;

 public:

  CPUCodeGen() : CodeGenBase() {
    suffix = "cpp";
  }

  /*
  std::string get_mask(int group_size, int id) {
    TC_ASSERT(0 <= id && id < group_size);
    TC_ASSERT(group_size < 1000);
    int key = group_size * 1000 + id;
    if (masks.find(key) == masks.end()) {
      auto l = loop_variable(prog->current_snode);
      auto mask_name = fmt::format("mask_{}_{}", group_size, id);
      CODE_REGION(residual_begin);
      std::vector<int> offsets;
      for (int i = 0; i < simd_width; i++) {
        offsets.push_back(i / group_size + id * (simd_width / group_size));
      }
      emit_code("auto {}_indices = add(vec<int32, {}>({}), {});", mask_name,
                simd_width, l,
                get_constant(fmt::format("vec<int32, {}>({})", simd_width,
                                         vec_to_list(offsets, "{"))));
      emit_code(
          "auto {} = cmp_lt({}_indices, vec<int32, {}>({}_cache->get_n()));",
          mask_name, mask_name, simd_width,
          prog->current_snode->node_type_name);
      masks[key] = mask_name;
    }
    return masks[key];
  }
  */


  void generate_header();

  void generate_tail();

  void codegen(Kernel &ker);

  FunctionType compile(Program &prog, Kernel &kernel);
};

using CodeGen = CPUCodeGen;

TLANG_NAMESPACE_END
