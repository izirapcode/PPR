<?php

	   function strToHex($string){
        $hex = '';
        for ($i=0; $i<strlen($string); $i++){
        $ord = ord($string[$i]);
        $hexCode = dechex($ord);
        $hex .= substr('0'.$hexCode, -2);
        }
        return strToUpper($hex);
    }
    
		function stringPass($data) {
		$host = "127.0.0.1";
        $port = 12345;
	   if(!($sock = socket_create(AF_INET, SOCK_DGRAM, 0)))
        {
        die("Couldn't create socket!\n");
        }
	
		#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		$stderr = fopen('php://stderr', 'w');
		fwrite( $stderr, "Client: $data\n" );
		 $input = strToHex($data);
        if( ! socket_sendto($sock, $input , strlen($input) , 0 , $host , $port))
        {
            die("Could not send data:!\n");
        } 
	}
    $server = new SoapServer("wsdl.wsdl");
	$server->addFunction("stringPass");
    $server->handle();
	

?>
