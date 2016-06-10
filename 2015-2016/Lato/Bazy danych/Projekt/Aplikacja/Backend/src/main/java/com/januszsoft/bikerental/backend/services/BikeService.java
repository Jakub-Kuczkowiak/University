package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.BikeDaoImpl;
import com.januszsoft.bikerental.backend.models.Bike;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/bike")
@Produces(MediaType.APPLICATION_JSON)
public class BikeService {

  @Autowired
  BikeDaoImpl bikes;

  @GET
  @Path("/")
  public Response getBikeInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(bikes.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getBikeInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Bike aBike = bikes.get(id);
    if(aBike == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aBike).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addBike(String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteBike(@PathParam("id") Integer id) {
    bikes.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeBikeBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
