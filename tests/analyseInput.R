xx=scan("analyseInput",what="",sep="\n")
nRow=as.numeric(xx[1])
nCol=nRow+1
xx=xx[-1]
xx=strsplit(xx,",")

A=matrix(NA,nRow,nCol)
nIter=50000
soln=matrix(NA,nIter,nRow)
for(ii in 1:nIter){
    nn=0
    for(i in 1:nRow){
       for(j in 1:nCol){
          nn=nn+1 
          cur=unlist(xx[[nn]])
          type=cur[1]
          cur=as.double(cur[-1])
          if(type=="custom" && length(cur)>1) A[i,j]=sample(cur,1,replace=T)
          if(type=="custom" && length(cur)==1) A[i,j]=cur
          if(type=="gauss") A[i,j]=rnorm(1,mean=cur[1],sd=cur[2])
          if(type=="unif") A[i,j]=runif(1,min=cur[1],max=cur[2])
          if(type=="exp") A[i,j]=rexp(1,cur[1])
       }
    }
    b=A[,nCol]
    AA=A[,1:nRow]
    soln[ii,]=solve(AA,b)
}
print(apply(soln,2,mean))
print(apply(soln,2,var))

par(mfrow=c(1,3))
hist(soln[,1],25)
hist(soln[,2],25)
hist(soln[,3],25)
