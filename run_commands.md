For openmp -------------------->

         g++ -fopenmp program_name.cpp -o binary_name.out && ./binary_name.out 

eg. g++ -fopenmp bubbleSort.cpp -o bubbleSort.out && ./bubbleSort.out 

  OR 
  
       g++ -fopenmp filename.cpp -o filename

      ./filename

CUDA on linux--------------------->

         nvcc program_name.cu -o binary_name.out && ./binary_name.out

OR

         nvcc programName.cu - o programName
         ./programName or programName


CUDA on colab------------------------>

click on runtime > change runtime type > Hardware accelerator > select > T4 GPU

       !nvcc --version
       !pip install git+git://github.com/andreinechaev/nvcc4jupyter.git
       %load_ext nvcc_plugin
       %%cuda 
       //ur code here

OR 

https://harshityadav95.medium.com/how-to-run-cuda-c-or-c-on-google-colab-or-azure-notebook-ea75a23a5962 

