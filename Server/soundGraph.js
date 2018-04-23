// Starting the script when the page is loaded
$( () =>
{
	var cnvs  = document.getElementById( "soundGraph" ); // Main canvas
	var ctx   = cnvs.getContext( "2d" );                 // Main context
	var soundGraph;      // Main chart object
    var sdata      = ""; // Sound data from the server ( string )
    var sdata_prev = ""; // Previous sound data from the server ( string )
    var fdata      = []; // Sound data from the server ( float array )
	var buff       = ""; // Transmission buffer for string to float parsing
	var i, j       = 0;  // Loop counters
	var data_update_delay = 500;              // Data update delay ( milliseconds )
	var server_json_file  = "last_line.json"; // Name of the file with
											  // the newest sound data on
											  // the server side
	
	/**
		Resises the canvas to the inner size parameters
		of the browser window

		Arguments: none
		Return: none
	*/
	function resize ()
    {
        cnvs.width  = window.innerWidth;  // Resizing the width
		cnvs.height = window.innerHeight; // Resizing the height	
	}

	/**
		Draws and sets parameters of the chart, assigns
		the final object to the soundGraph variable

		Arguments: none
		Return: none
	*/
	function makeChart () 
	{
		soundGraph = new Chart( ctx,
		{
			// Type of the drawn chart
			type : "line",
		    data :
		    {
				// Labels of each point on the graph
		        labels : [ "1", "2", "3", "4", "5", "6", "7", "8" ],
		        datasets :
		        [{
		            label : "FastDB",
		            data : fdata,
					borderCapStyle : "round",
				}]
			},
			// Additional settings
			options :
			{
				responsive : true,
		    	responsiveAnimationDuration : 500,
		    	maintainAspectRatio : false,
		    	layout :
		    	{
			        padding :
			        {
						left: 10,
			            right: 30,
			            top: 20,
			            bottom: 5,
			        },
		        },
		    	animation :
		    	{
		    		easing : "easeOutQuint",
		    		duration : 500,
		    	},
		    	legend :
		    	{
		    		display : true,
		    	},
		    	scales :
		    	{
		            yAxes :
		            [{
		            	// Showing all the Y-axis
		            	// values
		                stacked : true,
		            }]
		        },
		    	elements :
		    	{
		    		// The point parameters
		    		point :
		    		{
		    			pointStyle : "circle",
		    			backgroundColor : "pink",
						borderColor : "rgba( 0, 0, 0, 1 )",
						hoverRadius : 25,
		    			hoverBorderWidth : 5,
		    			radius : 10,
		    			borderWidth : 2,	
		    		},
		    		// Line parameters
		            line :
		            {
		            	backgroundColor : "rgba( 0, 0, 0, 0.5 )",
						borderColor : "rgba( 0, 0, 0, 1 )",
						borderWidth : 2,
		                tension : 0,
		            }
		        }
			}
		});
	}

	/**
		Gets the sound data from the last_line.json
		via jQuery implementation of AJAX

		Arguments: none
		Return: none
	*/
	function loadData ()
	{
		$.get(
			server_json_file,
			( data ) =>
			{
		        // Transferring the data string
				// into string variable sdata
				sdata = data[ "data" ];
			}
		);
	}

	/**
		Converts the string value of sdata variable
		into float array fdata

		Arguments: none
		Return: none
	*/
	function convertData ()
	{
		// String to float array convertion
		for ( i = 0, j = 0; i < sdata.length; ++i )
		{
			// Gets the sting of a number
			// until there is a semicolon
			if ( sdata[ i ] != ";" )
			{	
				// The string is passed into the buffer
				buff += sdata[ i ];
			}	
			else
			{
				// String to float array parsing of the buffer
				fdata[ j ] = parseFloat( buff );

				// Cleaning the string buffer and going
				// to the the next float array element
				buff  = "";				
				++j;	
			}
		}
	}

	/*
		Main function of the script
		
		Arguments: none
		Return: none
	*/
	function main ()
	{
		/*
			It is important to make the Chart object
			once and just update the data afterwards
			without making new Chart object, which
			optimizes the performance

			-----------------------------------------
		*/
		// Setting up jQuery AJAX properties
		$.ajaxSetup(
		{
			cache: false, // Disabling cache
			async: false  // Setting synchronous AJAX mode
		});

		loadData();

		// Saving currently received data into string
		// buffer sdata_prev
		sdata_prev = sdata.toString();

		convertData();
		makeChart(); // Making new chart

		//	-----------------------------------------

		/*
			The chart is requested at intervals in order
			to follow the real time data. If received
			data is new, it will be converted and the
			graph will be updated

			Interval is set by data_update_delay variable
		*/
		setInterval(
			() =>
			{
				loadData();

				// Disabling data convertion and graph updating
				// if there is no new data received
				if ( sdata_prev !== sdata )
				{
					// Saving currently received data into string
					// buffer sdata_prev
					sdata_prev = sdata.toString();

					convertData();
					soundGraph.update(); // Updating the chart
				}
			},
			data_update_delay
		);
	}


	// Resizing the canvas to fill browser window dynamically
	window.addEventListener( "resize", resize, false );
	
	main();
});