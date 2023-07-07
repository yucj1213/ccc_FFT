
function output = aie_srs( input, shift, DATA_WIDTH)

if ~exist('DATA_WIDTH', 'var')
	DATA_WIDTH = 16;
end


output_re = real(input); 
output_re = max(-2^(DATA_WIDTH-1), min(2^(DATA_WIDTH-1)-1, round(output_re/2^shift)));

output_im = imag(input);
output_im = max(-2^(DATA_WIDTH-1), min(2^(DATA_WIDTH-1)-1, round(output_im/2^shift)));

% combine real-imag parts to form output
output = complex(output_re,output_im);


