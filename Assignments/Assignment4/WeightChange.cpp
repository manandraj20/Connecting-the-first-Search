for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
		d[i][j]= min(d[i][j], d[i][u]+w+d[v][j]);
	}
}