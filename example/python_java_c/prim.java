public class prim{
	public static void main(String[] args){
		int i,j,k = 0,l;
		for(i = 2;i < (1 << 16);i++){
			l = (int)Math.sqrt(i);
			for(j = 2;j <= l;j++)
				if(i % j == 0){
					k++;
					break;
				}
		}
		System.out.println(k);
	}
}

