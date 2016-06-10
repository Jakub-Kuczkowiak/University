package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.PaymentDaoImpl;
import com.januszsoft.bikerental.backend.models.Payment;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/payment")
@Produces(MediaType.APPLICATION_JSON)
public class PaymentService {

  @Autowired
  PaymentDaoImpl payments;

  @GET
  @Path("/")
  public Response getPaymentInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(payments.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getPaymentInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Payment aPayment = payments.get(id);
    if(aPayment == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aPayment).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addPayment(@PathParam("id") Integer id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deletePayment(@PathParam("id") Integer id) {
    payments.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changePaymentBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
