f = read.csv(file.choose(),header=T,row.names=1)
f
plot(f)
k = kmeans(f,centers=4)
k
d = dist(f)
cah = hclust(d,method="ward.D2")
plot(cah)
