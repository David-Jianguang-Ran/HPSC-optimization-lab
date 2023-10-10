#! /bin/bash
# -
# |
# | Part 1: Directives
# |
# -

#SBATCH --nodes=1
#SBATCH --ntasks=10
#SBATCH --time=00:30:00
#SBATCH --partition=amilan
#SBATCH --output=slurm-test-run-%j.out

# -
# |
# | Part 2: Loading software
# |
# -

module purge
module load intel
module load impi
module load valgrind/3.17.0

# -
# |
# | Part 3: User scripting
# |
# -

echo "=="
echo "||"
echo "|| Begin Execution of esPIC in slurm batch script."
echo "||"
echo "=="

srun -n 4 valgrind --tool=cachegrind --cachegrind-out-file="cachegrind.test.out" ./esPIC -nPEx 2 -nPEy 2 -nCellx 40 -nCelly 40 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot > test-cache.out
srun -n 4 valgrind --tool=callgrind --callgrind-out-file="callgrind.test.out" ./esPIC -nPEx 2 -nPEy 2 -nCellx 40 -nCelly 40 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot > test-call.out

callgrind_annotate --auto=yes cachegrind.test.out >  cachegrind.test.txt

echo "=="
echo "||"
echo "|| Execution of esPIC in slurm batch script complete."
echo "||"
echo "=="