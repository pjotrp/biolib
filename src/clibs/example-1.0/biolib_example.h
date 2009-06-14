#ifdef __cplusplus
extern "C" {
#endif

  int fact(int n);
  int my_mod(int x, int y);
  char *get_time();
  float *list(int size);
  void matrix_as_array_change(int cols, int rows, double **matrix_as_array);
  // Three different ways of SWIG parameter passing
  void array_transform_to_result(int num, double *data, double *result);
  void array_transform_to_result1(int num, double *data1, double *result1);
  void array_transform_to_result2(int num, double *data2, double *result2);
  void array_transform_to_result3(int num, double *data3, double *result3);

#ifdef __cplusplus
}
#endif
