#ifdef __cplusplus
extern "C" {
#endif

  int fact(int n);
  int my_mod(int x, int y);
  char *get_time();
  float *list(int size);
  void matrix_as_array_change(int cols, int rows, double **matrix_as_array);
  void array_transform_to_result(int num, double *data, double *result);

#ifdef __cplusplus
}
#endif
