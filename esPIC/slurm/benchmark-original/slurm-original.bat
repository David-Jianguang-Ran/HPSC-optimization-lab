#! /bin/bash
# -
# |
# | Part 1: Directives
# |
# -

#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --time=02:00:00
#SBATCH --partition=amilan
#SBATCH --output=slurm-original-run-%j.out

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

srun -n 4 ./esPIC-original -nPEx 2 -nPEy 2 -nCellx 40 -nCelly 40 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> original-benchmark.out

srun -n 4 ./esPIC-original -nPEx 2 -nPEy 2 -nCellx 80 -nCelly 80 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> original-benchmark.out

srun -n 4 ./esPIC-original -nPEx 2 -nPEy 2 -nCellx 160 -nCelly 160 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> original-benchmark.out

echo "=="
echo "||"
echo "|| Execution of esPIC in slurm batch script complete."
echo "||"
echo "=="