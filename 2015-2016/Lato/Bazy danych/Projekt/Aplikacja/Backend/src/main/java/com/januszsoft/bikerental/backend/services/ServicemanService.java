package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.ServicemanDaoImpl;
import com.januszsoft.bikerental.backend.models.Serviceman;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/serviceman")
@Produces(MediaType.APPLICATION_JSON)
public class ServicemanService {

  @Autowired
  ServicemanDaoImpl servicemans;

  @GET
  @Path("/")
  public Response getServicemanInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(servicemans.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getServicemanInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Serviceman aServiceman = servicemans.get(id);
    if(aServiceman == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aServiceman).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addServiceman(@PathParam("id") Integer id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteServiceman(@PathParam("id") Integer id) {
    servicemans.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeServicemanBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
