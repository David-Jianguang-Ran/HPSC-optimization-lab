#! /bin/bash
# -
# |
# | Part 1: Directives
# |
# -

#SBATCH --nodes=1
#SBATCH --ntasks=16
#SBATCH --time=02:00:00
#SBATCH --partition=amilan
#SBATCH --output=slurm-combined-run-%j.out

# -
# |
# | Part 2: Loading software
# |
# -

module purge
module load intel
module load impi

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

srun -n 16 ./esPIC-combined -nPEx 4 -nPEy 4 -nCellx 20 -nCelly 20 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> combined-benchmark-2.out

srun -n 16 ./esPIC-combined -nPEx 4 -nPEy 4 -nCellx 40 -nCelly 40 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> combined-benchmark-2.out

srun -n 16 ./esPIC-combined -nPEx 4 -nPEy 4 -nCellx 80 -nCelly 80 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> combined-benchmark-2.out

srun -n 16 ./esPIC-combined -nPEx 4 -nPEy 4 -nCellx 160 -nCelly 160 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> combined-benchmark-2.out

srun -n 16 ./esPIC-combined -nPEx 4 -nPEy 4 -nCellx 320 -nCelly 320 -nPtcl 100000  -flux 1000  -tEnd 1 -dt .01 -tPlot .2 -noPlot >> combined-benchmark-2.out

echo "=="
echo "||"
echo "|| Execution of esPIC in slurm batch script complete."
echo "||"
echo "=="