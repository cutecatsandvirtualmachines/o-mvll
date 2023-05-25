// TODO: Require that the native target is registered.
// TODO: Make sure Clang finds a linker on our host machine.

// Failing with "ld: library not found for -lSystem" with system clang symlinked to LLVM_TOOLS_DIR
// XFAIL: host-platform-macOS

// Compilation can fail, e.g. if we insert invalid inline assembly.
// RUN:                                   clang -fno-legacy-pass-manager                         -O1 %s -o %T/basic-native
// RUN: env OMVLL_CONFIG=%S/config_all.py clang -fno-legacy-pass-manager -fpass-plugin=%libOMVLL -O1 %s -o %T/basic-native-obf

// This execution test only fails, if the below C code is invalid.
// RUN: %T/basic-native right
// RUN: not %T/basic-native wrong

// This execution test may fail, if our obfuscation is invalid.
// RUN: %T/basic-native-obf right
// RUN: not %T/basic-native-obf wrong

int check_password(const char* passwd) {
  if (passwd[0] == 'r') {
    if (passwd[1] == 'i') {
      if (passwd[2] == 'g') {
        if (passwd[3] == 'h') {
          if (passwd[4] == 't') {
            return 0;
          }
        }
      }
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc <= 1)
    return 2;
  return check_password(argv[1]);
}
