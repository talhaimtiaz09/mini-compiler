#ifndef ICG_UTILS_H
#define ICG_UTILS_H

void generateAssignment(const char* lhs, const char* rhs);
void generateBinaryOp(const char* result, const char* arg1, const char* op, const char* arg2);
const char* newTemp();
void initICGOutput();
void closeICGOutput();

#endif
