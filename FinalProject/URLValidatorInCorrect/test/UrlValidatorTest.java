

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   if(urlVal.isValid("http://www.google.com"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com:1234"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com:1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com:65100"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com/a"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com/a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com/a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com?a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google.com?a=1/ab=test"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com:1234"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com:1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com:65100"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com/a"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com/a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com/a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com?a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.amazon.com?a=1/b=2"))
	   {System.out.print("SSSSSuccess");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com:1234"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com:1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com:65100"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com/a"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com/a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com/a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com?a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("https://www.amazon.com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com:1234"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com:1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com:65100"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com/a"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com/a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com/a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com?a=1"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("ftp://www.google.com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google. com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www..com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("www.google.com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http:www.google.com?a=1/b=2"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google."))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http://www.google"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("http"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}

	   if(urlVal.isValid("random string"))
	   {System.out.print("Success");}
	   else {System.out.print("Failure");}
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   
   
   // Programmatic Testing 
 
   
   public class TestURL {
	   // Parts of the TestURL
	   private String scheme = "";
	   private String authority = "";
	   private String port = "";
	   private String path = "";
	   private String query = "";
	   // Expected validity of the TestURL
	   private Boolean validity = true;
	   
	   // Our TestURL Good Options
	   public String[] goodSchemes = { "http://", "https://", "ftp://", "h3t://", "" };
	   public String[] goodAuthorities = { "www.google.com", "www.icann.org", "www.oregonstate.edu", "oregonstate.edu", "secure.oregonstate.com" };
	   public String[] goodPorts = { ":80", ":8080", ":20", ":0", "" };
	   public String[] goodPaths = { "/path", "/path/subpath", "/otherpath/", "/123abc$", "" };
	   public String[] goodQueries = { "?search=term", "?search=term&page=1", "?search=one+two", "?action=nothing", "" };
	   
	   // Our TestURL Bad Options
	   public String[] badSchemes = { "abc://", "://", "http:/", "<#>://", "://http" };
	   public String[] badAuthorities = {  "wwwwww.oregon.state.eedduu", "edu.oregonstate.", "oregonstate..edu", "www.com", "" };
	   public String[] badPorts = {  ":99999", ":-99999", ":abc", ":###", ":0a1b" };
	   public String[] badPaths = { "\\path", "../", "/path/..", "/../../path", "/../path/.." };
	   public String[] badQueries = { "?search=/?/", "!search=&term", "term=search?", "?search=termpage=one", "search?=term" };
	   
	   // Base Constructor
	   public TestURL() {
		   super();
		   
		   // Set the URL
		   scheme = "http://";
		   // scheme = goodSchemes[ (int)( Math.random() * goodSchemes.length ) ];
		   authority = goodAuthorities[ (int)( Math.random() * goodAuthorities.length ) ];
		   port = goodPorts[ (int)( Math.random() * goodPorts.length ) ];
		   path = goodPaths[ (int)( Math.random() * goodPaths.length ) ];
		   query = goodQueries[ (int)( Math.random() * goodQueries.length ) ];
		  
		   validity = true;
		   
	   }
	   
	   
	   // Base getters
	   public String getScheme() { return scheme; }
	   public String getAuthority() { return authority; }
	   public String getPort() { return port; }
	   public String getPath() { return path; }
	   public String getQuery() { return query; }
	   public Boolean getValidity() { return validity; }
	   
	   // Get TestURL as URL string
	   public String getValidURL() {
		   return scheme + authority + port + path + query;
	   }
	   
	   // Makes a selected part of the TestURL invalid
	   public String getInvalidURL(int option) {
		   switch ( option ) {
			   case 1:
				   return badSchemes[ (int)( Math.random() * badSchemes.length ) ] + authority + port + path + query;
			   case 2:
				   return scheme + badAuthorities[ (int)( Math.random() * badAuthorities.length ) ] + port + path + query;
			   case 3:
				   return scheme + authority + badPorts[ (int)( Math.random() * badPorts.length ) ] + path + query;
			   case 4:
				   return scheme + authority + port + badPaths[ (int)( Math.random() * badPaths.length ) ] + query;
			   case 5:
				   return scheme + authority + port + path + badQueries[ (int)( Math.random() * badQueries.length ) ];
			   case 6:
				   return scheme + authority + port + path + query;
			   default:
				   return scheme + authority + port + path + query;
		   }
	   }
	   
   }
   
   public String getURLPart(String[] options ) {
	   int ran = (int)( Math.random() * 10 );
	   return options[ran];
   }
   
   public void testIsValid()
   {

	   boolean testStatus = false, expectedStatus = false;
	   int runs = 0, bugs = 0, successes = 0;	   	   
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));
	   
	   
	   while( true ) {
		   
		   // Build a new TestURL
		   TestURL tester = new TestURL();
		   
		   String url = "";
		   
		   for( int idx = 0; idx < 7; idx++ ) {
			   
			   if( idx == 0 ) {
				   // Get the valid TestURL string
				   url = tester.getValidURL();
				   expectedStatus = true;
			   } else {
				   // Get a bad TestURL string
				   url = tester.getInvalidURL( idx );
				   expectedStatus = false;
			   }
			   
			   System.out.println( "[ " + idx + " ] " + "CURRENT URL: " + url );

			   // Test the URL using isValid()
			   try { testStatus = urlVal.isValid( url ); }
			   catch(Exception e) { System.out.println( "BUG: " + e ); continue; }
			   
			   // Determine the status of the test
			   //assertEquals(url, expectedStatus, testStatus);
			   
			   if( testStatus == expectedStatus ) {
				   successes++;
			   } else {
				   System.out.println( "[ BAD URL ]" );
			   }
						  
			  
		   }
		   
		   if ( successes != 7 ) {
			   // Unexpected result returned
			   bugs++;
		   }
		   
		   
		   successes = 0;
		   runs++;
		   
		   if( runs > 100 ) { break; }
		   
	   }
	   
	   
	   System.out.println( "BUGS ENCOUNTERED: " + bugs );

   }
   


}
