<?php
	$log_file        = 'sound_log.txt';   // Log file
	$last_line_file  = 'last_line.json';  // Last 8-bytes of sound data in .json format

	/**
		If the data is being transmitted, it will be
		appended / written into log TXT file ( $log_file ),
		depending on whether the file exists;
		the last received line of sound data will be
		overwritten in the JSON file ( $last_line_file )
		
		If the data is not being transmitted, the presence
		of JSON file ( $last_line_file ) will be checked.
		If it exists, this PHP code will do nothing, but
		if it doesn't exist, this code will inform the user,
		that the data is unreachable
	*/
	if ( isset( $_POST[ 'data' ] ) )
	{
		$data = $_POST[ 'data' ];       // The sound data that was received ( string )
		$today = date( "Y-m-d H:i:s" ); // Current date ( string )
		
		/*
			Comdination of the current date ( $today )
			and data ( $data ) in a string ( $str ), followed
			by the PHP_EOL constant
		*/
		$str = $today . ', ' . $data . PHP_EOL;
		
		// Opening the file to store the info
		if ( file_exists( $log_file ) && file_exists( $sound_data_file ) )
		{
			// Appending info to the $log_file
			$fp_log = fopen( $log_file, "a" );
		}
		else
		{
			// Making a new $log_file
			$fp_log = fopen( $log_file, "w");
		}

		// Overrwriting / making a new JSON file ( $last_line_file )
		$fp_json = fopen( $last_line_file, "w");
		
		// Making the array with the sound data ( $data )
		$last_line_file_content = array( 'data' => $data );
		
		// Writing the data
		fwrite( $fp_log, $str );
		fwrite( $fp_json, json_encode( $last_line_file_content ) );

		// Closing files
		fclose( $fp_log );
		fclose( $fp_json );
	}
	else
	{	
		// JSON file ( $last_line_file ) check
		if ( !file_exists( $last_line_file ) )
		{
			// If it doesn't exist, the program will inform the user
			echo "The last_line.json does not exist. Data is unreachable";
		}
		include "sound.html";
	}
?>