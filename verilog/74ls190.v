module hc190(data_in, clk, enable, dwn_up, load, data_out, ripple, tc);

input [3:0]data_in;
input clk,enable,dwn_up,load;
output [3:0]data_out;
output ripple, tc;
reg [3:0] data_out;
reg tc;

assign ripple=!(!enable&tc&!clk);

always @(posedge clk or negedge load) begin
    if (load == 0) begin // 异步置数
        data_out<=data_in;
    end
    else if (!enable) begin //启用
        if(!dwn_up) begin //顺数
            if (data_out<9) data_out<=data_out+1; //对于 0~8
            else if (data_out == 9) data_out<=0; //对于 9
            else if(data_out%2==0) data_out<=data_out+1; //对于 10,12,14
            else data_out<=17-data_out; //对于 15,13,11
        end
        else begin //倒数
            if (data_out==0) data_out<=9;
            else data_out<=data_out-1;
        end
    end
end

always @(posedge clk)
    tc<=(dwn_up==0 && data_out==9 || dwn_up==1 && data_out==0);
//顺数时输出为9后进位，倒数时输出为0后进位

endmodule