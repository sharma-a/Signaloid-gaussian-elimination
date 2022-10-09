nRow=7

N=nRow*(nRow+1)
mus=runif(N,-100,100)
sigmas=sqrt(abs(mus))/50
ff=file("Mixinput",open="w")
cat(nRow,"\n",file=ff,sep="")
for(i in 1:length(mus)){
   if (i%%4==0 )cat("gauss",",",mus[i],",",sigmas[i],"\n",file=ff,sep="")
   if (i%%4==1) cat("unif",",",abs(mus[i])*.8,",",abs(mus[i])*1.2,"\n",file=ff,sep="")
   if (i%%4==2) cat("custom",",",mus[i],"\n",file=ff,sep="")
   if (i%%4==3) cat("custom",",",mus[i], "," ,mus[i]*runif(1,1,1.2),",",mus[i]*runif(1,1,1.3),"\n",file=ff,sep="")
}

close(ff)
