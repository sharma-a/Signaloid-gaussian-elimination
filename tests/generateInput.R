nRow=6

N=nRow*(nRow+1)
mus=runif(N,-100,100)
sigmas=sqrt(abs(mus))/50
ff=file("input_new",open="w")
cat(nRow,"\n",file=ff,sep="")
for(i in 1:length(mus)){
   kk=sample(1:4,1)
   if (kk==1)cat("gauss",",",mus[i],",",sigmas[i],"\n",file=ff,sep="")
   if (kk==2) cat("unif",",",abs(mus[i])*.92,",",abs(mus[i])*1.07,"\n",file=ff,sep="")
   if (kk==3) cat("custom",",",mus[i],"\n",file=ff,sep="")
   if (kk==4) cat("custom",",",mus[i], "," ,mus[i]*runif(1,1,1.2),",",mus[i]*runif(1,1,1.3),"\n",file=ff,sep="")
}

close(ff)
