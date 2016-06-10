package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.IssueDaoImpl;
import com.januszsoft.bikerental.backend.models.Issue;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/issue")
@Produces(MediaType.APPLICATION_JSON)
public class IssueService {

  @Autowired
  IssueDaoImpl issues;

  @GET
  @Path("/")
  public Response getIssueInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(issues.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getIssueInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Issue anIssue = issues.get(id);
    if(anIssue == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(anIssue).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addIssue(String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteIssue(@PathParam("id") Integer id) {
    issues.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeIssueBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
