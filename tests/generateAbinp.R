nRow=4

N=nRow*(nRow+1)
mus=runif(N,-100,100)
sigmas=sqrt(abs(mus))/50
ff=file("Abinp",open="w")
cat(nRow,"\n",file=ff,sep="")
for(i in 1:length(mus)){
   cat(mus[i],",",sigmas[i],"\n",file=ff,sep="")
}

close(ff)
