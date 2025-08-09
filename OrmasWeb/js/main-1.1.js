$(document).ready(function(){              
	$.ajax({
	type: 'POST',
	url: '/list.php',
	success: function(data){
		$('.ajax-content').html(data);
	}
    });
	
	$('#show-list').addClass('current');
	
	//add additional html
	$('.ajax-content').on('click','.form-button-content',function(){
		function collback(options){
			var html = "<div class='addable'> \
						<div class='close-bar'> \
							<div class='close-img'> \
							</div> \
						</div> \
						<div class='my-row'>\
							<div class='float-left'>\
								<label class='float-left form-label'>Виберите продукт:</label>\
								<select class='form-prod' name='product[]'>";
							html = html	+ options;
							html = html +	"</select>\
							</div>\
							<div >\
								<label class='float-left form-label'>Количество:</label>\
								<input class ='form-count' type='number' name='count[]'/>\
							</div>\
						</div>\
					</div>";
			$('.form-content').append(html);
			$('.form-content .form-prod').each(function(i, obj) {
				$( this ).select2({
				placeholder: '',
				allowClear: false
				});
				//console.log(i);
			});
		}
		$.ajax({type: 'POST',	url: '/product_list.php', success: function(data){ collback(data);}});
	});
	
	//delete additional html
	$('.ajax-content').on('click','.close-img',function(){
		$(this).parent().parent().empty();
	});
	//chage by click 
	
	
	
	//create order
	$('#create-order').on('click',function(){
		$('div').removeClass('current');
		$('#create-order').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/order.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
		//ajax call
		/*$.ajax({
			type: 'POST',
			url: '/load_clients.php',
			success: function(data){
				$('.select-clinets').html(data);
			}
		});*/
	});
	
	//create return
	$('#create-return').on('click',function(){
		$('div').removeClass('current');
		$('#create-return').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/return.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//show list
	$('#show-list').on('click',function(){
		$('div').removeClass('current');
		$('#show-list').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/list.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//search element
	$('#search-element').on('click',function(){
		$('div').removeClass('current');
		$('#search-element').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/find.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//transport element
	$('#transport').on('click',function(){
		$('div').removeClass('current');
		$('#transport').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/transport.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//report
	$('#report').on('click',function(){
		$('div').removeClass('current');
		$('#report').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/report.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	
	//my balance
	$('#balance').on('click',function(){
		$('div').removeClass('current');
		$('#balance').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_balance.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//clients balances
	$('#clients-balance').on('click',function(){
		$('div').removeClass('current');
		$('#clients-balance').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/clients_balance.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//my expeditor
	$('#expeditor').on('click',function(){
		$('div').removeClass('current');
		$('#expeditor').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_expeditor.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//my clients
	$('#clients').on('click',function(){
		$('div').removeClass('current');
		$('#clients').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_clients.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//add client
	$('#add-client').on('click',function(){
		$('div').removeClass('current');
		$('#add-client').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/add_client.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//payment
	$('#payment').on('click',function(){
		$('div').removeClass('current');
		$('#payment').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/payment.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//consume
	$('#consume').on('click',function(){
		$('div').removeClass('current');
		$('#consume').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/consume_product.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//raw-orders
	$('#show-raw-orders').on('click',function(){
		$('div').removeClass('current');
		$('#show-raw-orders').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/raw_orders.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	//puteyor-balnce
	$('#purveyors-balance').on('click',function(){
		$('div').removeClass('current');
		$('#purveyors-balance').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/purveyors_balance.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	//purveyors
	$('#my-purveyors').on('click',function(){
		$('div').removeClass('current');
		$('#my-purveyors').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_purveyors.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	//my-balance
	$('#my-balance').on('click',function(){
		$('div').removeClass('current');
		$('#my-balance').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_balance.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//price
	$('#price').on('click',function(){
		$('div').removeClass('current');
		$('#price').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/price.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//my_payments
	$('#my_payments').on('click',function(){
		$('div').removeClass('current');
		$('#my_payments').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/my_payments.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
	
	//order raw
	$('#order-raw').on('click',function(){
		$('div').removeClass('current');
		$('#order-raw').addClass('current');
		$('.ajax-content').empty();
		//ajax call
		$.ajax({
			type: 'POST',
			url: '/history.php',
			success: function(data){
				$('.ajax-content').html(data);
			}
		});
	});
});


	
function Report()
{
	$('div').removeClass('current');
	$('.report').addClass('current');
	var date = $('#datepicker').val();
	alert(date);
	//ajax call
	$.ajax({
		type: 'POST',
		data: { datepicker: date} ,
		url: '/report_response.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
}

function Calculate(type)
{
	if(type == "Consume")
	{
		var jsonFalseObject = JSON.parse(document.getElementsByName('falsePrices')[0].value);
	}
	var jsonObject = JSON.parse(document.getElementsByName('prices')[0].value);
	var productObjects = document.getElementsByClassName('form-prod');
	var countObjects = document.getElementsByClassName('form-count');
	var totalCount;
	var totalSum;
	if(productObjects.length == countObjects.length)
	{
		totalCount = Number(0);
		totalSum = Number(0.0);
		if(type == "Consume")
		{
			totalFalseSum = Number(0.0);
		}
		for(i=0; i < productObjects.length; i++)
		{
			totalCount += Number(countObjects[i].value);
			jsonObject.forEach(function(item, j, jsonObject) {
				if(item.id == productObjects[i].value)
				{
					totalSum += Number(Number(item.price)*Number(countObjects[i].value));
				}
			});
			if(type == "Consume")
			{
				jsonFalseObject.forEach(function(item, j, jsonFalseObject) {
				if(item.id == productObjects[i].value)
				{
					totalFalseSum += Number(Number(item.price)*Number(countObjects[i].value));
				}
				});
			}
		}
	}
	document.getElementById('sum').value = Math.round(totalSum * 100)/100;
	if(type == "Order")
	{
		document.getElementById('ordercount').value = Math.round(totalCount* 100)/100;
	}
	if(type == "Return")
	{
		document.getElementById('returncount').value = Math.round(totalCount* 100)/100;
	}
	if(type == "Consume")
	{
		document.getElementById('falseSum').value = Math.round(totalFalseSum * 100)/100;
		document.getElementById('consumecount').value = Math.round(totalCount* 100)/100;
	}
}

//submit form
function SubmitOrderForm()
{
	Calculate("Order");
	var exitStatus = false;
	if($("#selected-clinet").val() == null)
	{
		alert("Поле 'Клиент' не может быть пустым!");
		exitStatus = true;
	}
	if(exitStatus)
		return false;
	$(".ajax-content").hide();
	
	html = "<div class='accept-form'>\
	<div class='form-title'>\
		<label>Ваш заказ</label>\
	</div>";
	
	var count = new Array();
	var prod = new Array();
	$('.form-content .form-prod').each(function(i, obj) {
				prod.push($(this).text());
			});
	$('.form-content .form-count').each(function(i, obj) {
				count.push($( this ).val());
			});
	
	var divForAdd = ""
	if(prod.length == count.length)
	{
		var i;
		for(i = 0; i < prod.length; i++)
		{
			if(count[i]>0)
			{
				divForAdd += "<div class='my-row'>";
				divForAdd += "<label class='float-left approve-label'>"+prod[i]+"</label>";
				divForAdd += "<label class='approve-label'>"+count[i]+"</label>";
				divForAdd += "</div>";
			}
		}
	}
	html += divForAdd;
	html +="<div class= 'row'>\
				<label class='float-left form-label'>На сумму:</label>\
				<label id='sum-lb' class='float-left approve-price'>";
	html += $("#sum").val() == null ? 0 : $("#sum").val();
	html +="</label> <label class='float-left form-label'>Сомони</label>\
		</div>\
		<div class= 'row'>\
		</div>\
		<div class= 'row'>\
			<input class='accept-submit float-left' type='button' value='Назад' onclick='CancelForm()' id='can-button' />\
			<input class='accept-submit' type='submit' value='Подтвердить' onclick='ApproveOrderForm()' id='app-button' />\
		</div>\
	</div>";
	$(".content-body").append(html);
}

//submit form
function SubmitConsumeForm()
{
	Calculate("Consume");
	$(".ajax-content").hide();
	
	html = "<div class='accept-form'>\
	<div class='form-title'>\
		<label>Ваша заявка</label>\
	</div>";
	
	var count = new Array();
	var prod = new Array();
	$('.form-content .form-prod').each(function(i, obj) {
				prod.push($(this).text());
			});
	$('.form-content .form-count').each(function(i, obj) {
				count.push($( this ).val());
			});
	
	var divForAdd = ""
	if(prod.length == count.length)
	{
		var i;
		for(i = 0; i < prod.length; i++)
		{
			if(count[i]>0)
			{
				divForAdd += "<div class='my-row'>";
				divForAdd += "<label class='float-left approve-label'>"+prod[i]+"</label>";
				divForAdd += "<label class='approve-label'>"+count[i]+"</label>";
				divForAdd += "</div>";
			}
		}
	}
	html += divForAdd;
	html +="<div class= 'row'>\
				<label class='float-left form-label'>На сумму:</label>\
				<label id='sum-lb' class='float-left approve-price'>";
	html += $("#falseSum").val() == null ? 0 : $("#falseSum").val();
	html +="</label> <label class='float-left form-label'>Сомони</label>\
		</div>\
		<div class= 'row'>\
		</div>\
		<div class= 'row'>\
			<input class='accept-submit float-left' type='button' value='Назад' onclick='CancelForm()' id='can-button' />\
			<input class='accept-submit' type='submit' value='Подтвердить' onclick='ApproveConsumeForm()' id='app-button' />\
		</div>\
	</div>";
	$(".content-body").append(html);
}

//submit form
function SubmitOrderFormForClient()
{
	Calculate("Order");
	var exitStatus = false;
	if($("#employee").val() == null)
	{
		alert("Поле 'Экспедитор' не может быть пустым, джите активации Вашего аккаунта!");
		exitStatus = true;
	}
	if(exitStatus)
		return false;
	$(".ajax-content").hide();
	
	html = "<div class='accept-form'>\
	<div class='form-title'>\
		<label>Ваш заказ</label>\
	</div>";
	
	var count = new Array();
	var prod = new Array();
	$('.form-content .form-prod').each(function(i, obj) {
				prod.push($(obj).children("option").filter(":selected").text());
			});
	$('.form-content .form-count').each(function(i, obj) {
				count.push($( this ).val());
			});
	
	var divForAdd = ""
	if(prod.length == count.length)
	{
		var i;
		for(i = 0; i < prod.length; i++)
		{
			if(count[i]>0)
			{
				divForAdd += "<div class='my-row'>";
				divForAdd += "<label class='float-left approve-label'>"+prod[i]+"</label>";
				divForAdd += "<label class='approve-label'>"+count[i]+"</label>";
				divForAdd += "</div>";
			}
		}
	}
	html += divForAdd;
	html +="<div class= 'row'>\
				<label class='float-left form-label'>На сумму:</label>\
				<label id='sum-lb' class='float-left approve-price'>";
	html += $("#sum").val() == null ? 0 : $("#sum").val();
	html +="</label> <label class='float-left form-label'>Сомони</label>\
		</div>\
		<div class= 'row'>\
		</div>\
		<div class= 'row'>\
			<input class='accept-submit float-left' type='button' value='Назад' onclick='CancelForm()' id='can-button' />\
			<input class='accept-submit' type='submit' value='Подтвердить' onclick='ApproveOrderForm()' id='app-button' />\
		</div>\
	</div>";
	$(".content-body").append(html);
}

function SubmitReturnForm()
{
	Calculate("Return");
	var exitStatus = false;
	if($("#selected-clinet").val() == null)
	{
		alert("Поле 'Клиент' не может быть пустым!");
		exitStatus = true;
	}
	if(exitStatus)
		return false;
	$(".ajax-content").hide();
	
	html = "<div class='accept-form'>\
	<div class='form-title'>\
		<label>Список возврата</label>\
	</div>";
	
	var count = new Array();
	var prod = new Array();
	$('.form-content .form-prod').each(function(i, obj) {
				prod.push($(this).text());
			});
	$('.form-content .form-count').each(function(i, obj) {
				count.push($( this ).val());
			});
	
	var divForAdd = ""
	if(prod.length == count.length)
	{
		var i;
		for(i = 0; i < prod.length; i++)
		{
			if(count[i]>0)
			{
				divForAdd += "<div class='my-row'>";
				divForAdd += "<label class='float-left approve-label'>"+prod[i]+"</label>";
				divForAdd += "<label class='approve-label'>"+count[i]+"</label>";
				divForAdd += "</div>";
			}
		}
	}
	
	html += divForAdd;
	html +="<div class= 'row'>\
				<label class='float-left form-label'>На сумму:</label>\
				<label id='sum-lb' class='float-left approve-price'>";
	html += $("#sum").val() == null ? 0 : $("#sum").val();
	html +="</label> <label class='float-left form-label'>Сомони</label>\
		</div>\
		<div class= 'row'>\
		</div>\
		<div class= 'row'>\
			<input class='accept-submit float-left' type='button' value='Назад' onclick='CancelForm()' id='can-button' />\
			<input class='accept-submit' type='submit' value='Подтвердить' onclick='ApproveReturnForm()' id='app-button' />\
		</div>\
	</div>";
	$(".content-body").append(html);
}

function SubmitReturnFormForClinet()
{
	Calculate("Return");
	var exitStatus = false;
	if($("#employee").val() == null)
	{
		alert("Поле 'Экспедитор' не может быть пустым, джите активации Вашего аккаунта!");
		exitStatus = true;
	}
	if(exitStatus)
		return false;
	$(".ajax-content").hide();
	
	html = "<div class='accept-form'>\
	<div class='form-title'>\
		<label>Список возврата</label>\
	</div>";
	
	var count = new Array();
	var prod = new Array();
	$('.form-content .form-prod').each(function(i, obj) {
				prod.push($(obj).children("option").filter(":selected").text());
			});
	$('.form-content .form-count').each(function(i, obj) {
				count.push($( this ).val());
			});
	
	var divForAdd = ""
	if(prod.length == count.length)
	{
		var i;
		for(i = 0; i < prod.length; i++)
		{
			if(count[i]>0)
			{
				divForAdd += "<div class='my-row'>";
				divForAdd += "<label class='float-left approve-label'>"+prod[i]+"</label>";
				divForAdd += "<label class='approve-label'>"+count[i]+"</label>";
				divForAdd += "</div>";
			}
		}
	}
	
	html += divForAdd;
	html +="<div class= 'row'>\
				<label class='float-left form-label'>На сумму:</label>\
				<label id='sum-lb' class='float-left approve-price'>";
	html += $("#sum").val() == null ? 0 : $("#sum").val();
	html +="</label> <label class='float-left form-label'>Сомони</label>\
		</div>\
		<div class= 'row'>\
		</div>\
		<div class= 'row'>\
			<input class='accept-submit float-left' type='button' value='Назад' onclick='CancelForm()' id='can-button' />\
			<input class='accept-submit' type='submit' value='Подтвердить' onclick='ApproveReturnForm()' id='app-button' />\
		</div>\
	</div>";
	$(".content-body").append(html);
}

function CancelForm()
{
	$(".accept-form").remove();
	$(".ajax-content").show();
}

function ApproveOrderForm()
{
	if($("#sum").val() == null || $("#sum").val() == 0)
	{
		alert ("Список товаров пуст! Сначала выберите товар!");
	}
	else
	{
		document.getElementById("order-form").submit();
	}
}

function ApproveReturnForm()
{
	if($("#sum").val() == null || $("#sum").val() == 0)
	{
		alert ("Список товаров пуст! Сначала выберите товар!");
	}
	else
	{
		document.getElementById("return-form").submit();
	}
}

function ApproveConsumeForm()
{
	if($("#sum").val() == null || $("#sum").val() == 0)
	{
		alert ("Список товаров пуст! Сначала выберите товар!");
	}
	else
	{
		document.getElementById("consume-form").submit();
	}
}

function ExecuteOrder($order_id)
{
	if(confirm("Этот документ будет исполнен! Подтверждаете?\nНажмине ОК или Отмена.")==true)
	{
		document.getElementById("execute").value=$order_id;
		document.getElementById("execute-order").submit();
	}
}

function ExecuteReturn($return_id)
{
	if(confirm("Этот документ будет исполнен! Подтверждаете?\nНажмине ОК или Отмена.")==true)
	{
		document.getElementById("execute-return").value=$return_id;
		document.getElementById("execute-ret").submit();
	}
}



function CancelOrder($order_id)
{
	if(confirm("Этот документ будет удален! Подтверждаете?\nНажмине ОК или Отмена.")==true)
	{
		document.getElementById("order_error").value=$order_id;
		document.getElementById("cancel-order").submit();
	}
}

function CancelReturn($return_id)
{
	if(confirm("Этот документ будет удален! Подтверждаете?\nНажмине ОК или Отмена.")==true)
	{
		document.getElementById("return-error").value=$return_id;
		document.getElementById("cancel-return").submit();
	}
}

function CancelConsume($consume_id)
{
	if(confirm("Этот документ будет удален! Подтверждаете?\nНажмине ОК или Отмена.")==true)
	{
		document.getElementById("consume-error").value=$consume_id;
		document.getElementById("cancel-consume").submit();
	}
}

function PrintOrder(orderID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "order-id": orderID, 
		},
		url: '/print.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
}

function PrintProductCons(prodConsID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "cons-id": prodConsID, 
		},
		url: '/print.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
}

function PrintReturn(returnID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "return-id": returnID, 
		},
		url: '/print.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
	
}

function PrintConsume(consumeID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "consume-id": consumeID, 
		},
		url: '/print.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
	
}

function PrintOrderRaw(orderRawID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "order-raw-id": orderRawID, 
		},
		url: '/print.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
	
}

function TermoPrintOrder(orderID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "order-id": orderID, 
		},
		url: '/termoprint.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
}


function TermoPrintReturn(returnID)
{
	$('.report-content').empty();
	$.ajax({
		type: 'POST',
		 data: { 
        "return-id": returnID, 
		},
		url: '/termoprint.php',
		success: function(data){
			$('.ajax-content').append(data);
		}
	});
	
}

function SentToPrinter()
{
	var content = "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'><html xmlns='http://www.w3.org/1999/xhtml'><head></head><body font-size='30px'><div style='min-width:600px;'>"
	content += document.getElementById("modal-content").innerHTML;
	content += "</div></body ></html>"
	var myWindow = window.open("","_blank", "");
	myWindow.document.write(content);
	myWindow.document.close();
	myWindow.focus();
	myWindow.print();
	
}

function CloseModal()
{
	$('.modal').remove();
}

function CloseModalAuto()
{
	$('.modal-auto').remove();
}


