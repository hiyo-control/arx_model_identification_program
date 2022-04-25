CC = g++
CFLAGS = -o

ALL: 0_output_backward_difference\
	 1_preprocessing\
	 2_impulse_estimate\
	 3_arx_structure\
	 4_zero_pole_calculation\
	 5_arx_model_reduction

### Cpp & header file for 0_output_backward_difference ###
LIBS_0  = ./include/0_output_backward_difference_function.h
LIBS_0 += ./include/backward_difference.cpp
LIBS_0 += ./include/csv_import.cpp
LIBS_0 += ./include/csv_import.h

### Cpp & header file for 1_preprocessing ###
LIBS_1  = ./include/1_preprocessing_function.h
LIBS_1 += ./include/average_calc.cpp
LIBS_1 += ./include/remove_trend.cpp
LIBS_1 += ./include/low_pass_filter.cpp
LIBS_1 += ./include/csv_import.cpp
LIBS_1 += ./include/csv_import.h

### Cpp & header file for 2_impulse_estimate ###
LIBS_2  = ./include/2_impulse_estimate_function.h
LIBS_2 += ./include/correlation_analysis_method.cpp
LIBS_2 += ./include/csv_import.cpp
LIBS_2 += ./include/csv_import.h

### Cpp & header file for 3_arx_structure ###
LIBS_3  = ./include/3_arx_structure_function.h
LIBS_3 += ./include/inv_matrix.cpp
LIBS_3 += ./include/max.cpp
LIBS_3 += ./include/min.cpp
LIBS_3 += ./include/vector_phi_k.cpp
LIBS_3 += ./include/vector_f.cpp
LIBS_3 += ./include/matrix_R.cpp
LIBS_3 += ./include/arx_coefficient_calc.cpp
LIBS_3 += ./include/arx_coefficient_matrix.cpp
LIBS_3 += ./include/y_k_estimate.cpp
LIBS_3 += ./include/y_estimate_matrix.cpp
LIBS_3 += ./include/loss_function_calc.cpp
LIBS_3 += ./include/coefficient_select.cpp
LIBS_3 += ./include/csv_import.cpp
LIBS_3 += ./include/csv_import.h

### Cpp & header file for 4_zero_pole_calculation ###
LIBS_4  = ./include/4_zero_pole_calculation_function.h
LIBS_4 += ./include/polynomial_roots_calculation.cpp
LIBS_4 += ./include/polynomial_value.cpp
LIBS_4 += ./include/polynomial_derivative.cpp
LIBS_4 += ./include/csv_import.cpp
LIBS_4 += ./include/csv_import.h

### Cpp & header file for 5_arx_model_reduction ###
LIBS_5  = ./include/csv_import.cpp
LIBS_5 += ./include/csv_import.h


0_output_backward_difference: 0_output_backward_difference.cpp
	$(CC) $(CFLAGS) 0_output_backward_difference 0_output_backward_difference.cpp $(LIBS_0)

1_preprocessing: 1_preprocessing.cpp
	$(CC) $(CFLAGS) 1_preprocessing 1_preprocessing.cpp $(LIBS_1)

2_impulse_estimate: 2_impulse_estimate.cpp
	$(CC) $(CFLAGS) 2_impulse_estimate 2_impulse_estimate.cpp $(LIBS_2)

3_arx_structure: 3_arx_structure.cpp
	$(CC) $(CFLAGS) 3_arx_structure 3_arx_structure.cpp $(LIBS_3)

4_zero_pole_calculation: 4_zero_pole_calculation.cpp
	$(CC) $(CFLAGS) 4_zero_pole_calculation 4_zero_pole_calculation.cpp $(LIBS_4)

5_arx_model_reduction: 5_arx_model_reduction.cpp
	$(CC) $(CFLAGS) 5_arx_model_reduction 5_arx_model_reduction.cpp $(LIBS_5)