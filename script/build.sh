curr_dir=$(dirname "$0")

cmake -S ${curr_dir}/../.. -B ${curr_dir}/../../build
cmake --build ${curr_dir}/../../build
cd ${curr_dir}/../../build
./UniversityTimetablingSystem
./tests
