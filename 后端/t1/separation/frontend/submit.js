$(document).ready(function(){
	var inf_name_zh = ['姓名', '性别', '年龄', '手机号']
	var inf_name_en = ['name', 'gender', 'age', 'phone']
	$('#submit').click(function(){
		var url = $('#form').attr('action');
		var data = $('#form').serialize();
		console.log(url);
		console.log(data);
		$.get(url, data, function(respond){
			$('#info').empty();
			resp_data = jQuery.parseJSON(respond);
			console.log(resp_data)
			let f = 1
			for(let i = 0; i < 4; i++){
				$('#' + inf_name_en[i]).empty();
				if(resp_data[i] == 0){
					$('#' + inf_name_en[i]).append('<span class = "green"> √ </span>');
				}
				if(resp_data[i] == 1){
					$('#' + inf_name_en[i]).append('<span class = "red"> ' + inf_name_zh[i] + '不能为空' + ' </span>');
					f = 0;
				}
				else if(resp_data[i] == 2){;
					$('#' + inf_name_en[i]).append('<span class = "red">' + inf_name_zh[i] + '已经被提交过' + '</span>')
					f = 0;
				}
			}
			if(f){
				$('#info').append('提交成功！');
			}
		})
	})
})