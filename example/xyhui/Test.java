package 刷校邮汇;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;


public class Main_Test {
	static DefaultHttpClient httpClient;
	static HttpResponse response;
	static class Test_Item{
		public String question;
		public String Answer;
	};
	static ArrayList<Test_Item> Test_List = new ArrayList<>();
	/**
	 * @param _something Just for fun
	 */
	public static void main(String[] _something){
		while(true){
			httpClient = new DefaultHttpClient();
			HttpPost Login_Post = new HttpPost("http://xyhui.com/index.php?app=wap&mod=Public&act=doLogin");
			List<NameValuePair> nvps = new ArrayList<NameValuePair>();  
	        nvps.add(new BasicNameValuePair("email", "1127403096@mysuda.com"));  
	        nvps.add(new BasicNameValuePair("password", "111111"));  
	        nvps.add(new BasicNameValuePair("remember", "1"));
	        try {
				Login_Post.setEntity(new UrlEncodedFormEntity(nvps, HTTP.UTF_8));
				response = httpClient.execute(Login_Post);  
				Login_Post.abort();
				//system.out.println(response.getStatusLine());
				HttpGet Test_Get = new HttpGet("http://xyhui.com/index.php?app=exercise&mod=Index&act=go");
				ResponseHandler<String> responseHandler = new BasicResponseHandler();  
		        String responseBody = "";  
		        responseBody = httpClient.execute(Test_Get, responseHandler); 
		        String[] Questions = responseBody.split("<div class=\"exam_list_ti");
		        int i = 0;
		        ArrayList<String> All = new ArrayList<>();
		        for (String string : Questions) {
		        	All.add(string);
		        }
		        All.remove(0);
		        All.remove(All.size() - 1);
		        for (String string : All) {
		        	String tmpQuestion = new String(), tmpKey = new String(); 
		        	//string = string.replaceAll(".", ":");
		        	Pattern pattern = Pattern.compile("(tle\">[0-9].)(.+?)(</div>)");
		        	Matcher matcher = pattern
		        		    .matcher(string);
		        	if(matcher.find()) {
		        	      //system.out.println(matcher.group(2));
		        	      tmpQuestion = matcher.group(2);
		        	} else {
		        		pattern = Pattern.compile("(tle\">.)(.+?)(</div>)");
			        	matcher = pattern.matcher(string);
			        	//system.out.println(matcher.group(2));
		        	    tmpQuestion = matcher.group(2);
					}
		        	
		        	if(string.contains("xz")){
		        		String[] tmp = string.split("<label><input type=\"radio\"");
		        		for (String string2 : tmp) {
		        			pattern = Pattern.compile("(/>)(.+?)(</label>)");
				        	matcher = pattern.matcher(string2);
			        		if(matcher.find()){
			        			//system.out.println(matcher.group(2));
			        			tmpKey += matcher.group(2) + "\n";
			        		}
						}
						
		        	}
		        	pattern = Pattern.compile("(class=\"exam_list_answer\">)(.+?)(</div>)");
		        	matcher = pattern.matcher(string);
		        	while (matcher.find()) {
		        	      //system.out.println(matcher.group(2));
		        	      tmpKey += matcher.group(2);
		        	}
		        	Test_Item item = new Test_Item();
		        	String aString = ".";
		        	tmpQuestion = tmpQuestion.replace(aString, "");
		        	String Key_UTF8 = java.net.URLEncoder.encode(tmpKey, "UTF-8"); 
		        	String Question_UTF8 = java.net.URLEncoder.encode(tmpQuestion, "UTF-8"); 
		        	item.Answer = Key_UTF8;
		        	item.question = Question_UTF8;
		        	//System.out.println(Question_UTF8);
		        	//System.out.println(Key_UTF8);
		        	Test_List.add(item);
				}
		        writeSQL(Test_List);
		        Test_List.clear();
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			} catch (ClientProtocolException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}  
		}
	}
	
	public static void writeSQL(ArrayList<Test_Item> _tmp) throws Exception{
		Class.forName("com.mysql.jdbc.Driver");	//加载驱动
		String url = "jdbc:mysql://192.168.135.113:3306/test";
		Connection con = DriverManager.getConnection(url, "fpp","fpp");
		
		String sql =( "insert into Test_List values(?,?);");
		PreparedStatement cmd = con.prepareStatement(sql);
		for (int i = 0; i < _tmp.size(); i++) {
			cmd.setString(1, _tmp.get(i).question);
			cmd.setString(2, _tmp.get(i).Answer);
			try{
				cmd.execute();
			}catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		ResultSet rs = cmd.executeQuery("select * from Test_List;");
		int i = 0;
		while(rs.next()){
			String Question = URLDecoder.decode(rs.getString(1));
        	String Answer = URLDecoder.decode(rs.getString(2));
        	System.out.println(Question);
        	System.out.println(Answer);
        	i++;
    	}
		System.out.println("ALL:" + i);
		con.close();
	}
}

