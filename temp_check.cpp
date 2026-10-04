#include "common/cli.h"
int main() { atlas::Config c; return atlas::parse_arguments(0, nullptr, c) ? 0 : 1; }
