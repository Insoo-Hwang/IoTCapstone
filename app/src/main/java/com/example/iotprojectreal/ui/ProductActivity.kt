package com.example.iotprojectreal.ui

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.amazonaws.mobile.client.Callback
import com.example.iotprojectreal.databinding.ActivityProductBinding
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import okhttp3.RequestBody
import okhttp3.ResponseBody
import org.json.JSONObject
import retrofit2.Call
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.Body
import retrofit2.http.POST

class ProductActivity : AppCompatActivity() {
    lateinit var binding : ActivityProductBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityProductBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.button5.setOnClickListener {
            val Loc = binding.Loctext.text.toString()
            val Name = binding.Nametext.text.toString()
            val Price = binding.Pricetext.text.toString()
            val A = binding.Atext.text.toString().toInt()
            val B = binding.Btext.text.toString().toInt()
            val C = binding.Ctext.text.toString().toInt()
            val D = binding.Dtext.text.toString().toInt()
            val E = binding.Etext.text.toString().toInt()
            val F = binding.Ftext.text.toString().toInt()
            val Age = binding.Agetext.text.toString().toInt()
            val Gender = binding.Gendertext.text.toString()
            val retrofit = Retrofit.Builder()
                .baseUrl("https://xo6g05qwcg.execute-api.ap-northeast-2.amazonaws.com/test/")
                .addConverterFactory(GsonConverterFactory.create())
                .build()
            val apiInterface = retrofit.create(MyApi2::class.java)
            val jsonObject = JSONObject()
            jsonObject.put("Location", Loc)
            jsonObject.put("Name", Name)
            jsonObject.put("Price", Price)
            jsonObject.put("A", A)
            jsonObject.put("B", B)
            jsonObject.put("C", C)
            jsonObject.put("D", D)
            jsonObject.put("E", E)
            jsonObject.put("F", F)
            jsonObject.put("Age", Age)
            jsonObject.put("Gender", Gender)

            val requestBody = RequestBody.create("application/json".toMediaTypeOrNull(), jsonObject.toString())

            apiInterface.postData(requestBody).enqueue(object : Callback<ResponseBody?>,
                retrofit2.Callback<ResponseBody> {
                override fun onResult(result: ResponseBody?) {
                    TODO("Not yet implemented")
                }

                override fun onError(e: java.lang.Exception?) {
                    TODO("Not yet implemented")
                }

                override fun onResponse(
                    call: Call<ResponseBody>,
                    response: Response<ResponseBody>
                ) {
                    System.out.println("성공")
                    binding.Loctext.text.clear()
                    binding.Nametext.text.clear()
                    binding.Pricetext.text.clear()
                    binding.Atext.text.clear()
                    binding.Btext.text.clear()
                    binding.Ctext.text.clear()
                    binding.Dtext.text.clear()
                    binding.Etext.text.clear()
                    binding.Ftext.text.clear()
                    binding.Agetext.text.clear()
                    binding.Gendertext.text.clear()
                }

                override fun onFailure(call: Call<ResponseBody>, t: Throwable) {
                    TODO("Not yet implemented")
                }
            })
        }

        binding.searchButton.setOnClickListener {
            val Loc = binding.searchText.text.toString()
            val retrofit = Retrofit.Builder()
                .baseUrl("https://n6wgvy3ela.execute-api.ap-northeast-2.amazonaws.com/test/")
                .addConverterFactory(GsonConverterFactory.create())
                .build()
            val apiInterface = retrofit.create(MyApi2::class.java)
            val jsonObject = JSONObject()
            jsonObject.put("Location", Loc)

            val requestBody = RequestBody.create("application/json".toMediaTypeOrNull(), jsonObject.toString())

            apiInterface.postData(requestBody).enqueue(object : Callback<ResponseBody?>,
                retrofit2.Callback<ResponseBody> {
                override fun onResult(result: ResponseBody?) {
                    TODO("Not yet implemented")
                }

                override fun onError(e: java.lang.Exception?) {
                    TODO("Not yet implemented")
                }

                override fun onResponse(
                    call: Call<ResponseBody>,
                    response: Response<ResponseBody>
                ) {
                    val responseString = response.body()?.string().toString()
                    val jsonResponse = JSONObject(responseString)
                    val bodyString = jsonResponse.getString("body")
                    val bodyJson = JSONObject(bodyString)
                    val location = bodyJson.getString("Location")
                    val name = bodyJson.getString("Name")
                    val price = bodyJson.getString("Price")

                    val resultText = "위치: $location\n제품명: $name\n가격: $price"
                    binding.result.text = resultText
                }

                override fun onFailure(call: Call<ResponseBody>, t: Throwable) {
                    TODO("Not yet implemented")
                }
            })
        }
    }
}

interface MyApi2 {
    @POST("greeting")
    fun postData(@Body requestBody: RequestBody): Call<ResponseBody>
}
